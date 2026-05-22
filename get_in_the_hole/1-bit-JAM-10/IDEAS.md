# File Warden

A 1-bit game about inspecting files, catching viruses, and surviving the queue. Built with C + raylib. CRT shader. 800x600. Web export.

---

## Concept

You're a file security analyst. Files arrive in your queue. Your job: inspect each one and decide to Approve (safe) or Delete (virus). Wrong decisions cost you strikes. Three strikes and it's over.

Files aren't static. They glitch, replicate, mimic clean files, and try to trick you. The pressure builds as the queue fills faster.

---

## Input Methods

Two ways to play, used together:
- **Mouse UI** – buttons for quick actions (open, approve, delete, flag)
- **Terminal** – a command line for deep inspection (hex dumps, metadata, string extraction, file comparison)

Mouse handles the final decision. Terminal handles investigation. Both are required to catch sophisticated threats.

---

## Gameplay Loop

Files stack in a queue on the left. Select a file to inspect. Use terminal commands to dig into its contents. Look for inconsistencies: mismatched metadata, suspicious hex patterns, hidden strings, glitching behavior. Decide to approve or delete. Correct decisions clear the file and add to your score. Wrong decisions add a strike and speed up incoming files.

---

## File Types

- **Clean files** – normal documents, system files, legitimate data. Should be approved.
- **Viruses** – malicious files with tells like repeating hex patterns, ransom strings, fake metadata. Should be deleted.
- **Decoys** – files designed to look viral but contain notes saying they're tests. Approve or delete based on context.
- **Glitching files** – change their contents mid-inspection. Forces quick decisions.
- **Replicating files** – spawn duplicates if left open too long. Prioritize or get flooded.
- **Moral files** – technically viruses but contain evidence or confessions. Deletion is correct gameplay but has narrative consequences.

---

## Progression

The game escalates over time:
- **Early** – simple files with obvious tells. Learn the commands.
- **Mid** – mixed queues. Files that mimic clean patterns. Glitching appears.
- **Late** – sophisticated threats. Multiple red herrings. Replicating files. Moral dilemmas.
- **Endgame** – a "boss" file that requires combining multiple terminal commands to identify correctly.

---

## Visual Style

1-bit black and white. CRT shader with scan lines and slight screen bend. 4:3 aspect ratio (800x600). Terminal uses classic monospace aesthetic. The CRT effect ties directly to gameplay – glitching files are visible as flickering or shifting text in the terminal output.

---

## Win Condition

Survive the workday. Clear a target number of files correctly. Each wave of files gets harder, but you unlock better scanning tools as you progress.

---

## Tone

Papers Please meets a terminal-based investigative thriller. The files tell stories – you're not just spotting viruses, you're deciding what to do with corrupted evidence, stolen data, and things that shouldn't exist on a normal workday.
