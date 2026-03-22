package cortex.isolation

import rego.v1

# Prevent cross-repo instruction leakage.
# Repo-specific instructions (repo != null) only surface when the
# requesting context matches that repo. Framework-agnostic instructions
# (repo == null) are always allowed.

default allow := true

allow if {
	input.instruction.repo == null
}

allow if {
	input.instruction.repo == input.request.repo
}

deny if {
	input.instruction.repo != null
	input.instruction.repo != input.request.repo
}
