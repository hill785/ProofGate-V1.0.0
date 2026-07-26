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

docker-compose.yml
version: '3.8'

services:
  # Node 1 acts as the master maintenance coordinator
  proofgate-node-1:
    build: .
    volumes:
      - shared-tmp-space:/tmp
    environment:
      - NODE_ID=1

  # Node 2 acts as a concurrent actor feeding load into the lock dir
  proofgate-node-2:
    build: .
    volumes:
      - shared-tmp-space:/tmp
    environment:
      - NODE_ID=2

  # Node 3 replicates an adversarial network cluster trying to trigger race conditions
  proofgate-node-3:
    build: .
    volumes:
      - shared-tmp-space:/tmp
    environment:
      - NODE_ID=3

volumes:
  # Shared data volume context simulating parallel cluster attachments for file locks
  shared-tmp-space:
