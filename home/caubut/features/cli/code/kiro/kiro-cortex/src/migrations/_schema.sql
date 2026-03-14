\restrict igkgvAFujQw5pXRGaXkKbSFcu9vStb3UBW5HYiuYAkNtyHOlBpFfQCFJHURfrs5

CREATE EXTENSION IF NOT EXISTS vector WITH SCHEMA public;

COMMENT ON EXTENSION vector IS 'vector data type and ivfflat and hnsw access methods';

CREATE TABLE public.effect_sql_migrations (
    migration_id integer NOT NULL,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    name text NOT NULL
);

CREATE TABLE public.instructions (
    id uuid DEFAULT gen_random_uuid() NOT NULL,
    text text NOT NULL,
    domain character varying(100),
    subdomain character varying(100),
    tier_access integer[],
    agent_roles text[],
    task_types text[],
    priority character varying(20),
    version character varying(20),
    dependencies uuid[],
    conflict_group character varying(100),
    embedding public.vector(768),
    created_at timestamp without time zone DEFAULT now(),
    updated_at timestamp without time zone DEFAULT now(),
    source character varying(255),
    repo character varying(255),
    effective_date timestamp without time zone,
    expiry_date timestamp without time zone
);

ALTER TABLE ONLY public.effect_sql_migrations
    ADD CONSTRAINT effect_sql_migrations_pkey PRIMARY KEY (migration_id);

ALTER TABLE ONLY public.instructions
    ADD CONSTRAINT instructions_pkey PRIMARY KEY (id);

CREATE INDEX instructions_agent_roles_idx ON public.instructions USING gin (agent_roles);

CREATE INDEX instructions_domain_subdomain_idx ON public.instructions USING btree (domain, subdomain);

CREATE INDEX instructions_embedding_idx ON public.instructions USING hnsw (embedding public.vector_cosine_ops);

CREATE INDEX instructions_task_types_idx ON public.instructions USING gin (task_types);

\unrestrict igkgvAFujQw5pXRGaXkKbSFcu9vStb3UBW5HYiuYAkNtyHOlBpFfQCFJHURfrs5

\restrict cdOYGlCTLcU8ccCtRyQpdFvQB1AqjYfZcWkesjuwda4gPU9gy3rEXhWzbqD47rC

INSERT INTO public.effect_sql_migrations (migration_id, created_at, name) VALUES (1, '2026-03-13 13:36:44.80845-06', 'init');
INSERT INTO public.effect_sql_migrations (migration_id, created_at, name) VALUES (2, '2026-03-13 17:59:25.690662-06', 'add_instruction_columns');

\unrestrict cdOYGlCTLcU8ccCtRyQpdFvQB1AqjYfZcWkesjuwda4gPU9gy3rEXhWzbqD47rC