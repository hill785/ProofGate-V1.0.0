#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <time.h>
#include <errno.h>

#define PRIMARY_LOCK_DIR "/tmp/.swarm_lock_matrix"
#define PRIMARY_MAINT_LOCK "/tmp/.swarm_matrix.maintenance"

#define FALLBACK_LOCK_DIR "./.swarm_lock_matrix"
#define FALLBACK_MAINT_LOCK "./.swarm_matrix.maintenance"

#define BURST_THRESHOLD 50
#define MAX_RETRY 3

// Global dynamic configuration pointers
const char *active_lock_dir = PRIMARY_LOCK_DIR;
const char *active_maint_lock = PRIMARY_MAINT_LOCK;

char registered_lease[512] = "";

void cleanup_lease() {
    if (strlen(registered_lease) > 0) {
        unlink(registered_lease);
    }
}

// Runtime environment probe to guarantee writable directories
void resolve_operational_paths() {
    // Attempt to initialize primary cluster path
    if (mkdir(PRIMARY_LOCK_DIR, 0777) == 0 || errno == EEXIST) {
        // Run a small canary file verification check to guarantee write safety
        char test_path[512];
        snprintf(test_path, sizeof(test_path), "%s/.canary_%d", PRIMARY_LOCK_DIR, getpid());
        FILE *f = fopen(test_path, "w");
        if (f) {
            fclose(f);
            unlink(test_path);
            active_lock_dir = PRIMARY_LOCK_DIR;
            active_maint_lock = PRIMARY_MAINT_LOCK;
            return;
        }
    }
    
    // Failover sequence to local space isolation
    fprintf(stderr, "::warning:: Primary path blocked or read-only. Engaging fallback localized directory.\n");
    mkdir(FALLBACK_LOCK_DIR, 0777);
    active_lock_dir = FALLBACK_LOCK_DIR;
    active_maint_lock = FALLBACK_MAINT_LOCK;
}

int count_active_leases() {
    int count = 0;
    DIR *dir = opendir(active_lock_dir);
    if (!dir) return 0;
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, "tx_", 3) == 0) {
            count++;
        }
    }
    closedir(dir);
    return count;
}

void perform_maintenance() {
    int m_fd = open(active_maint_lock, O_CREAT | O_WRONLY, 0666);
    if (m_fd < 0) return;

    if (flock(m_fd, LOCK_EX | LOCK_NB) == 0) {
        DIR *dir = opendir(active_lock_dir);
        if (dir) {
            struct dirent *entry;
            time_t now = time(NULL);
            while ((entry = readdir(dir)) != NULL) {
                if (strncmp(entry->d_name, "tx_", 3) == 0) {
                    char filepath[512];
                    snprintf(filepath, sizeof(filepath), "%s/%s", active_lock_dir, entry->d_name);
                    
                    struct stat st;
                    if (stat(filepath, &st) == 0) {
                        if (now - st.st_mtime > 60) {
                            unlink(filepath);
                        }
                    }
                }
            }
            closedir(dir);
        }
        flock(m_fd, LOCK_UN);
    }
    close(m_fd);
}

int verify_hashes() {
    int status256 = system("sha256sum --check expected.sha256 > /dev/null 2>&1");
    if (status256 != 0) {
        fprintf(stderr, "::error:: Signature Collision Detected. Payload corrupted!\n");
        return 1;
    }
    return 0;
}

int main() {
    atexit(cleanup_lease);
    resolve_operational_paths();
    
    printf("=== ProofGate Industrial Native Anti-Swarm Layer ===\n");
    printf("Active Security Zone: %s\n", active_lock_dir);

    int attempt = 0;
    while (attempt < MAX_RETRY) {
        snprintf(registered_lease, sizeof(registered_lease), "%s/tx_%ld_%d", active_lock_dir, (long)time(NULL), getpid());
        FILE *f = fopen(registered_lease, "w");
        if (f) fclose(f);

        perform_maintenance();
        int active_load = count_active_leases();

        if (active_load <= BURST_THRESHOLD) {
            if (verify_hashes() == 0) {
                printf("✓ ProofGate Lineage Uncompromised. Swarm Attack Blocked successfully.\n");
                return 0;
            }
            return 1;
        }

        attempt++;
        int delay = 1 << attempt;
        if (delay > 15) delay = 15;

        fprintf(stderr, "::warning:: Active Swarm Stress Detected (%d active transactions). Retrying... Backing off for %d seconds\n", active_load, delay);
        
        cleanup_lease();
        sleep(delay);
    }

    fprintf(stderr, "::error:: Boundary Invalidation. Sustained Swarm Load exceeded capacity.\n");
    return 1;
}
