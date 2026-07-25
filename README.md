# ProofGate-V1.0.0 # 🔒 ProofGate

**ProofGate** is a sovereign cyber‑security primitive: a gate that only opens when cryptographic proof is verified.  
It fuses **Zero‑Trust Verifier** with **QUITNLOCK deterministic locks**, producing evidence‑grade proof of identity, intent, and authority.

---

## ✨ Features
- **Digest Enforcement**: SHA‑256 + SHA‑512 capsule verification  
- **DAO Seals**: Immutable governance under MintProofDAO seal `436351437` and LedgerProofDAO seal `430`  
- **Wallet Binding**: Signing and royalties wallets cryptographically tied to capsule lineage  
- **On‑Chain Proof**: Verified Etherscan signature (#320378)  
- **ProofGate Combo**: Continuous identity verification fused with deterministic lock protocols  

---

## 📂 Repository Structure
- `capsule_manifest.json` → Canonical digest and ProofGate clause  
- `LICENSE` → Open Source (Apache 2.0 + Sovereign Addendum)  
- `LICENSE_COMMERCIAL.md` → Commercial SaaS license with royalties enforcement  
- `SCHEMA.md` → Documentation of repo structure and enforcement rules  
- `verify.sh` → Digest + Etherscan verification script  
- `/lineage` → CIDv1 and DAO seals metadata  
- `/docs` → Governance clauses, significance, verification workflows  
- `/badges` → DAO seal badges and QR‑coded capsule flyer  
- `/releases` → Tagged artifacts and provenance records  

---

## 🛠 Verification

### Digest Check
```bash
sha256sum capsule_manifest.json
# Expected: 87083a071221545ccd61c8fefe495c84f7ef903dcb8d6c0c88093f54534011f2

sha512sum capsule_manifest.json
# Expected: ce3dbe7968f1434a0811ccb4fe88584ad2429bd50e6d6f96fa950ae814b0ac0baa6820260f7de0f0e3e11fa5703d00eaf0ffe68748b70797ac3c12a5d200a37e
