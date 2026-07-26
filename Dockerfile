# Use a minimal, security-hardened Linux distribution as the base layer
FROM alpine:3.20

# Install dependencies required to compile native code and run validation scripts
RUN apk add --no-cache \
    build-base \
    bash \
    coreutils \
    util-linux

# Set up an unprivileged system user space boundary
RUN addgroup -S proofgroup && adduser -S proofuser -G proofgroup

WORKDIR /home/proofuser/proofgate
COPY . .

# Explicitly assign permissions across the workspace to prevent fallback permission bugs
RUN chown -R proofuser:proofgroup /home/proofuser/proofgate

# Compile the native cybersecurity primitive target inside the image context
RUN gcc -O3 -Wall -Wextra -D_POSIX_C_SOURCE=200809L -std=c99 scripts/verify_capsule.c -o scripts/verify_capsule && \
    chmod +x scripts/verify_capsule scripts/unit_tests.sh

# Drop process privileges down to the unprivileged container account 
USER proofuser

# Default execution entry point triggers the core unit test grid matrix
ENTRYPOINT ["./scripts/unit_tests.sh"]
