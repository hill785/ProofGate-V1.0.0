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