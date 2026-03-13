\restrict MO5yfxQ67OenmKyFvxFagpv70ZYvDwcT6UZjSo8iXjIOoJDu5A8SbPP2vWKbqg1

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
    updated_at timestamp without time zone DEFAULT now()
);

ALTER TABLE ONLY public.effect_sql_migrations
    ADD CONSTRAINT effect_sql_migrations_pkey PRIMARY KEY (migration_id);

ALTER TABLE ONLY public.instructions
    ADD CONSTRAINT instructions_pkey PRIMARY KEY (id);

CREATE INDEX instructions_agent_roles_idx ON public.instructions USING gin (agent_roles);

CREATE INDEX instructions_domain_subdomain_idx ON public.instructions USING btree (domain, subdomain);

CREATE INDEX instructions_embedding_idx ON public.instructions USING hnsw (embedding public.vector_cosine_ops);

CREATE INDEX instructions_task_types_idx ON public.instructions USING gin (task_types);

\unrestrict MO5yfxQ67OenmKyFvxFagpv70ZYvDwcT6UZjSo8iXjIOoJDu5A8SbPP2vWKbqg1

\restrict aVMNU086Nspbrgyo0Q6hy9YODxl11jeKZhMRIcpxCmEZqKmao9bwHqeYDsyQg60

INSERT INTO public.effect_sql_migrations (migration_id, created_at, name) VALUES (1, '2026-03-13 13:36:44.80845-06', 'init');

\unrestrict aVMNU086Nspbrgyo0Q6hy9YODxl11jeKZhMRIcpxCmEZqKmao9bwHqeYDsyQg60