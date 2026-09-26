# Clash projects

This is the shared navigation and documentation ownership guide for the Clash
repositories. Each project owns its implementation, setup instructions and
validation status. Follow the owning document for the current result; a success
in one repository does not establish completion in another.

## Choose a project

| Project | Purpose | Start here |
| --- | --- | --- |
| [clash-disassembly](https://github.com/lisu188/clash-disassembly) | Recover the original game's behavior as maintainable GNU++20 code with an SDL platform boundary. | [Documentation](README.md), [build and test](BUILD_AND_TEST.md), [current status](STATUS.md). |
| [clash-hd](https://github.com/lisu188/clash-hd) | Patch a verified original Windows executable for larger viewports and relocated UI, with a launcher and evidence tools. | [Documentation](https://github.com/lisu188/clash-hd/blob/main/docs/hd/README.md), [development](https://github.com/lisu188/clash-hd/blob/main/DEVELOPMENT.md), [validation matrix](https://github.com/lisu188/clash-hd/blob/main/reports/final_hd_validation_matrix.md). |
| [clash-save-editor / Clash Studio](https://github.com/lisu188/clash-save-editor) | Inspect and edit saves, create bounded free-game scenarios, and expose headless MCP save tools. | [Documentation](https://github.com/lisu188/clash-save-editor/blob/main/docs/README.md), [getting started](https://github.com/lisu188/clash-save-editor/blob/main/docs/getting-started.md), [current acceptance](https://github.com/lisu188/clash-save-editor/blob/main/docs/reverse-engineering/final-status.md). |
| [clash-assets](https://github.com/lisu188/clash-assets) | Preserve the English manual transcription and verified GOG runtime import provenance. | [README](https://github.com/lisu188/clash-assets#readme), [manual](https://github.com/lisu188/clash-assets/blob/main/Manual.md), [runtime import](https://github.com/lisu188/clash-assets/blob/main/sources/gog-32003/README.md). |

The reimplementation's final runtime expresses game behavior in C++. HD operates
on the original executable. Clash Studio edits data and does not run the game.
The assets repository supplies reference material and byte-level provenance.
These are complementary products with separate acceptance criteria.

## Documentation ownership

| Question | Authoritative location | What a cross-project reference should retain |
| --- | --- | --- |
| What behavior and binary layout have been recovered? | Disassembly source, manifests, [structures](STRUCTURES.md), [save format](SAVE_DAT_FORMAT.md) and original comparison evidence. | Symbol/field, source revision, observation and remaining uncertainty. |
| What does the reimplementation currently prove? | [STATUS](STATUS.md), [project tracks](PROJECT_TRACKS.md), machine-readable route fixtures and linked validation records. | Exact route, compiler/source revision and whether proof used direct mission load or the Campaign menu. |
| Which HD candidate or resolution is accepted? | HD resolution registry, current evidence reports, validation matrix and release checklist. | Input/candidate hashes, patch stage, dimensions and the evidence lane that passed. |
| Which save fields can be safely edited? | Clash Studio's core schema, [invariants](https://github.com/lisu188/clash-save-editor/blob/main/docs/reverse-engineering/invariants.md) and [safety guide](https://github.com/lisu188/clash-save-editor/blob/main/docs/reverse-engineering/safety-and-integrity.md). | Pinned recovery revision, supported field/transaction and byte-preservation limits. |
| Where did a manual or runtime file come from? | Assets manual metadata and GOG manifest/import record. | Original path, size, hash, transcription caveats and dated validation. |
| How do I build or validate a project? | That repository's setup guide and CI workflow. | Host/toolchain requirements and whether retail assets, a display or runtime input are required. |

Keep detailed offsets, commands, acceptance tables and evolving blockers in their
owning repository. Link them from other projects rather than copying a second
version. Pin a commit when another project depends on a specific recovered fact;
updating a link to newer recovery work does not by itself revalidate a consumer.

## Working across repositories

1. Identify the actual repository using its Git root and remote. Inspect the
   branch, working changes and repository instructions before editing. A WSL
   clone and a Windows checkout of the same remote are separate working states.
2. Begin at the project's README and current status owner. Dated batch reports,
   captured artifacts and archived plans describe their recorded revision.
3. Keep reference assets unchanged. Follow each project's own asset policy and
   use isolated writable runtime directories where required. Assets tracked in
   the assets repository are not authorization to copy binaries into the other
   repositories.
4. For changes that cross a boundary, record both revisions and the contract:
   executable hash for HD, field/layout evidence for the editor, or file hashes
   for an asset consumer. Verify consumer requirements rather than assuming that
   matching product names imply compatible layouts or environments.
5. Run checks that substantiate the changed claims. Preserve failures and missing
   evidence as explicit limitations, then update the canonical status owner and
   link the resulting evidence.

For example, the GOG import manifest's original executable hash matches the HD
README's expected base hash. That establishes the identity of those executable
bytes; it does not establish an HD runtime launch, wrapper behavior, or visual
acceptance. Similarly, the manual is useful for terminology and user flow, while
recovered control/data flow remains the authority for implementation semantics.

## Evidence vocabulary

| Evidence | Establishes | Further proof remains separate |
| --- | --- | --- |
| Documentation links, metadata and manifests | References resolve and declared inventories are internally consistent. | Build or runtime behavior. |
| Compilation, unit tests and synthetic fixtures | The tested source and cases pass under the recorded setup. | Complete gameplay or original parity. |
| Reimplementation route probes | The specific route reaches recorded states and acceptance markers. | Full Campaign-menu progression and whole-game completion. |
| HD hidden/debugger captures | The recorded candidate produces the observed route, state or software surface. | Final visible composition, authentic user input, soak and promotion. |
| Save round trips and structural validation | Tested bytes and supported transactions preserve their contracts. | Original-game acceptance of every exported scenario. |
| Asset hashes and LFS pointer validation | Recorded files or pointers match the manifest. | Download availability, installation or game launch. |
| Original-game comparison | The matched state has the recorded behavioral or visual agreement. | Unobserved states or unrelated subsystems. |

## Local copies and historical material

The September 2026 workspace review also found directories named `clash-batch`
and `clash-magic` with disassembly worktree pointers, a `clash-hd-preserved`
recovery directory, and a local `clash_mod` C++17 DLL-loading experiment without
a Git remote. They are not additional canonical repositories. Check their Git
metadata and preservation records before using them; folder names do not prove
that a checkout is current or that recovered drafts have been validated.

Preserve historical evidence when consolidating documentation. Move long batch
receipts to a clearly dated archive, keep navigable replacement links, and keep
current setup, status and task selection short. Documentation review must not
silently promote an unfinished runtime or erase an unresolved failure.
