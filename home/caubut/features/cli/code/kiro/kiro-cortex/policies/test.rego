package cortex.test

default allow = false
default deny = false

allow if {
    input.user_id != ""
}

deny if {
    contains(lower(input.query), "forbidden")
}

decision := {
    "allowed": allow,
    "denied": deny,
    "reason": reason,
}

reason := "missing user_id" if {
    input.user_id == ""
}

reason := "contains forbidden pattern" if {
    contains(lower(input.query), "forbidden")
}

reason := "allowed" if {
    allow
    not deny
}
