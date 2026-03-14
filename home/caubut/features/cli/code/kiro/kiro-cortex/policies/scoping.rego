package cortex.scoping

# Input: { agent_role, task_type, domain, repo }
# Output: filtering criteria for pgvector instruction search

filters := {
    "allowed_domains": allowed_domains,
    "allowed_task_types": allowed_task_types,
    "repo_filter": repo_filter,
    "max_results": max_results,
}

allowed_domains contains input.domain if {
    input.domain != ""
}

allowed_domains contains "global"

allowed_task_types contains input.task_type

repo_filter := input.repo if {
    input.repo != null
}

repo_filter := null if {
    input.repo == null
}

max_results := 50 if {
    input.task_type == "analysis"
}

max_results := 20 if {
    input.task_type != "analysis"
}
