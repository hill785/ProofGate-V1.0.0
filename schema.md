# 📘 ProofGate Repository Schema

This document defines the canonical structure of the **ProofGate** repository.  
ProofGate is a sovereign cyber‑security primitive that fuses **Zero‑Trust Verifier** with **QUITNLOCK deterministic locks**, producing evidence‑grade proof of identity, intent, and authority.

---

## 📂 Repository Layout
proofgate/
├── capsule_manifest.json      # Canonical digest + ProofGate clause
├── LICENSE                    # Apache 2.0 + Sovereign Addendum
├── LICENSE_COMMERCIAL.md      # Commercial SaaS license with royalties enforcement
├── README.md                  # Branding, tagline, verification instructions
├── SCHEMA.md                  # This schema document
├── verify.sh                  # Digest + Etherscan verification script
│
├── lineage/                   # Capsule lineage metadata
│   ├── cidv1_manifest.json    # CIDv1 pinning records
│   ├── dao_seals.json         # MintProofDAO + LedgerProofDAO seals
│
├── docs/                      # Governance clauses and workflows
│   ├── significance.md        # ProofGate significance clause
│   ├── governance.md          # DAO governance enforcement rules
│   ├── verification.md        # Digest + on‑chain verification steps
│
├── badges/                    # DAO seal badges + QR‑coded capsule flyer
│   ├── mintproof_seal.png
│   ├── ledgerproof_seal.png
│
└── releases/                  # Tagged artifacts and provenance records
    ├── provenance/            # Curated screenshots and evidence
    ├── v1.0/.0                  # Initial ProofGate release
`
🔒 Enforcement Rules

1. Capsule Lineage
   - capsulemanifest.json, cidv1manifest.json, and dao_seals.json must always remain tracked.
   - Immutable under MintProofDAO seal 436351437 and LedgerProofDAO seal 430.

2. Digest Verification
   - SHA‑256 and SHA‑512 digests must match expected values.
   - CI/CD pipelines must run verify.sh on every commit.

3. On‑Chain Proof
   - Signature ID 320378 must be validated via Etherscan.
   - Signing wallet 0x9e223F20022580739060d5511445C727f51Ee81e is canonical.
