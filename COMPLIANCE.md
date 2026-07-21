# COMPLIANCE.md

<<<<<<< HEAD
**Coastal Alpine Tech Limited** | **Product:** Sovereign Edge Firmware
Last updated: 19 July 2026

> Super Grok compliance briefing (19 July 2026). This is **alignment evidence**, not a compliance certificate or legal advice.

## Regulatory Mapping

### New Zealand
- Privacy Act 2020 + **IPP 3A** (Privacy Amendment Act 2025) - effective **1 May 2026**  
  Notification required when personal information is collected indirectly.
- Biometric Processing Privacy Code 2025  
  New biometric processing: 3 November 2025  
  Existing biometric processing: 3 August 2026
- Health Information Privacy Code (applies where health / wellbeing data is processed)
- Te Mana Raraunga principles - primary data sovereignty framework

### European Union
- **EU AI Act** - Annex III high-risk obligations enforceable **2 August 2026**
- Relevant high-risk categories:
  - Health decision support
  - Biometrics (remote identification, categorisation, emotion recognition)
  - Critical infrastructure / essential services
- Required: risk management, data governance, technical documentation, human oversight, logging, transparency, post-market monitoring

### International Standards
- **ISO/IEC 42001** - AI Management System (AIMS)  
  Covers AI policy, risk assessment, data governance, human oversight, monitoring, continual improvement
- **SOC 2** - Security, Availability, Confidentiality, Processing Integrity, Privacy  
  Priority for multi-tenant / customer-facing components

### Core Technical Controls (Mandatory)
- Local-first / offline-native processing by default
- Owner-controlled encryption keys
- No silent data exfiltration
- Explicit Human-in-the-Loop (HITL) gates for high-impact and culturally sensitive decisions
- Data residency under New Zealand control

### Scope Notes
- Current systems prioritise offline-native operation and data minimisation.
- Any future multi-tenant or customer-facing features will be assessed against SOC 2 and EU AI Act high-risk requirements before release.

### Limitations
- Not legal advice; not a certification claim.
- Confirm statute application with NZ counsel before commercial shipping claims.
- Agents inform / draft / prepare only; humans advise / sign / file / send / pay.
=======
**Coastal Alpine Tech Limited** | **Product:** Sovereign-Edge-Firmware  
Last updated: 2026-07-21

> Alignment evidence for Super Grok / CAT fleet reviews — **not** a compliance certificate or legal advice.

## Privacy · Security · Governance (fleet mandatory)

| Pillar | Standard |
| --- | --- |
| **Privacy** | Local-first default; purpose-limited collection; Privacy Act 2020; Te Mana Raraunga spirit; third-party processing only when opt-in and disclosed |
| **Security** | No silent exfil; owner-controlled credentials; least privilege; SecOps / red-team cadence on fleet repos where CI is present |
| **Governance** | HITL for high-stakes (billing, legal, production migrations, compliance templates, external send); agents draft only |

### New Zealand baseline
- Privacy Act 2020 (IPP awareness; indirect collection notification rules as applicable)
- Te Mana Raraunga principles as primary Māori data sovereignty lens
- Sector statutes called out in product-specific sections below when relevant

### Core technical controls
- Local-first / offline-native processing by default
- Owner-controlled encryption keys where implemented
- No silent data exfiltration to third parties
- Explicit HITL gates for high-impact and culturally sensitive decisions
- Prefer NZ / Oceania residency for any cloud components

### Limitations
- Not legal advice; not ISO/SOC/EU AI Act certification
- Confirm statute application with NZ counsel before regulated marketing claims

---
## Product notes

See README for product-specific controls.

>>>>>>> d6238bf (docs: emphasise privacy, security, and governance fleet-wide)
