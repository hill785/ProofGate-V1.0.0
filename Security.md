# Security Policy: ProofGate Sovereign Guard Matrix

We take the security of our zero-trust primitives, cryptographic verifiers, and deterministic lineage locks seriously. If you discover a vulnerability, memory leak, or agentic exploit, please report it via the coordinated disclosure process below.

## Supported Versions

Only the latest compiled native binary architectures receive active security patches. Legacy shell-script workflows (`.sh`) are deprecated and unpatched.

| Version | Supported          |
| ------- | ------------------ |
| v1.0.x  | :white_check_mark: |
| < v1.0.0| :x:                |

## Coordinated Disclosure Scope

We prioritize vulnerabilities addressing core protection mechanics, specifically map-aligned threats from the **OWASP Agentic Top 10**:

* **ASI01: Agent Goal Hijack** – Manipulation of instructions or verification decision paths to bypass lineage tracking.
* **ASI03: Identity and Privilege Abuse** – Exploits that leverage ambient runner configurations to escalate pipeline execution authority.
* **ASI05: Unexpected Code Execution** – System injections or escapes out of isolated validation wrappers into the host operating system.
* **ASI06: Context Poisoning** – Exploitation of the `capsule_manifest.json` structure to inject malicious metadata parameters into parsing runtime engines.

## Reporting a Vulnerability

**Do not open public GitHub issues, discussions, or pull requests for security vulnerabilities.** Public disclosure allows adversarial swarms to weaponize exploits before patches can be deployed.

Please submit a detailed security report to our dedicated, out-of-band security operations address:

📩 **security@proofgate.internal**

### Required Information
To help us validate your report quickly, please include:
1. **Threat Vector Classification:** State the relevant OWASP Agentic reference identifier.
2. **Environment Conditions:** Details on system architectures, runner profiles, and compiler parameters used.
3. **Proof of Concept (PoC):** A minimal reproducible test harness or payload array that demonstrates the vulnerability.

## Our Security Commitment

Upon receiving a valid vulnerability report, our core engineering team commits to the following timeline:

* **T + 24 Hours:** Initial verification, triaging, and acknowledgment of receipt.
* **T + 72 Hours:** Submission of a formal status update, detailing initial findings and reproduction status.
* **Remediation Phase:** A secure patch will be designed, stress-tested inside our parallel swarm simulation matrix, and merged into the main release lineage.
* **Coordinated Disclosure:** Public release notes and security advisories will be published only after upstream implementations have had adequate time to update their binary builds.
