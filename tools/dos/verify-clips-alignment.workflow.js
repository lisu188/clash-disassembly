export const meta = {
  name: 'verify-clips-alignment',
  description: 'Adversarially verify anchor-bounded CLIPS alignment proposals by comparing each DOS decompiled body to the named CLIPS 6.24 source function',
  phases: [{ title: 'Verify', detail: 'one skeptic per CLIPS module' }],
}
const parsedArgs = typeof args === 'string' ? JSON.parse(args) : args
const groups = parsedArgs.groups
const REPO = 'C:/Users/andrz/git/clash-disassembly'
const CLIPS = 'C:/Clash/ref/clips/624/CLIPSSrc/CLIPSSrc'

const SCHEMA = {
  type: 'object',
  required: ['verdicts'],
  properties: {
    verdicts: {
      type: 'array',
      items: {
        type: 'object',
        required: ['ea','proposed_name','verdict','reason'],
        properties: {
          ea: { type: 'string' },
          proposed_name: { type: 'string' },
          verdict: { type: 'string', enum: ['CONFIRM','REJECT','UNCERTAIN'] },
          corrected_name: { type: 'string', description: 'if the real match is a different CLIPS function, name it; else empty' },
          reason: { type: 'string', description: 'the structural evidence: matching constants, loop shape, callee pattern, string refs' },
        },
      },
    },
  },
}

phase('Verify')
const results = await parallel(groups.map(g => () =>
  agent(`You are an adversarial verifier for a reverse-engineering name-matching pipeline. A proposer used anchor-bounded sequence alignment (Watcom link order = source order within a compilation unit) to guess that certain DOS functions in the game "Clash" correspond to specific functions in CLIPS 6.24 source file **${g.clips_file}**. Your job is to CONFIRM or REJECT each, skeptically, from structural evidence — position alignment alone is NOT sufficient proof.

For each proposal below:
1. Read the DOS decompiled function: in ${REPO}/clash.c, find the line \`//----- (00<EA>) ---\` (EA is the proposal's ea without 0x, uppercased, 8 hex digits) and read that function body (until the next \`//----- (\` marker).
2. Read the proposed CLIPS source function: in ${CLIPS}/${g.clips_file}, find \`globle\`/\`static ... <proposed_name>(\` and read its body. (Strip a leading \`Env\` when searching if not found, and vice-versa.)
3. Compare STRUCTURE: distinctive integer/hex constants, number and shape of loops/branches, switch arms, string literals referenced, and the set of functions called (CLIPS callee names vs the DOS callees — DOS callees may be sub_XXXX or already-named). A genuine match shares magic constants and call/loop structure. A mismatch (different constants, incompatible control flow, wrong arity) => REJECT.
4. If you can identify the ACTUAL CLIPS function the DOS body matches (a different one in ${g.clips_file}), put it in corrected_name.

Be strict: default to UNCERTAIN if the evidence is thin, REJECT if structure conflicts, CONFIRM only when distinctive structural evidence agrees. Report a verdict for EVERY proposal.

Proposals for ${g.clips_file}:
${g.proposals.map(p => `  ea=${p.ea} proposed=${p.name} confidence=${p.confidence} proposer_evidence="${p.evidence}"`).join('\n')}`,
    { label: `verify:${g.clips_file}`, phase: 'Verify', schema: SCHEMA, effort: 'high' })
    .then(r => ({ clips_file: g.clips_file, verdicts: (r && r.verdicts) || [] }))
))

const all = results.flatMap(r => r.verdicts)
const confirmed = all.filter(v => v.verdict === 'CONFIRM')
const rejected = all.filter(v => v.verdict === 'REJECT')
const uncertain = all.filter(v => v.verdict === 'UNCERTAIN')
const corrections = all.filter(v => v.corrected_name && v.corrected_name.trim())
log(`verified ${all.length}: ${confirmed.length} CONFIRM, ${rejected.length} REJECT, ${uncertain.length} UNCERTAIN, ${corrections.length} with corrections`)
return { confirmed, rejected, uncertain, corrections, all }