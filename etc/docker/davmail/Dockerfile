ARG BASE_IMAGE=openjdk:8-jre-alpine

FROM alpine:3.18 AS builder

ARG DAVMAIL_REV=3422

ARG EXCLUDE_ARTIFACTIDS='winrun4j,servlet-api,junit,swt,growl'
ARG EXCLUDE_GROUPIDS='org.boris.winrun4j,javax.servlet,junit,org.eclipse,info.growl'

RUN apk add --update --no-cache openjdk8 maven subversion bash

RUN svn co -r ${DAVMAIL_REV} https://svn.code.sf.net/p/davmail/code/trunk /davmail-code

RUN cd /davmail-code\
 && mvn clean package\
 && mvn dependency:resolve\
     -DexcludeArtifactIds="${EXCLUDE_ARTIFACTIDS}"\
     -DexcludeGroupIds="${EXCLUDE_GROUPIDS}"\
     -DoutputAbsoluteArtifactFilename=true\
     -DoutputFile=/tmp/dependencies

RUN mkdir -vp /target/davmail /target/davmail/lib

RUN mv -v $(sed -ne 's/^.*:\([^:]*\.jar\)$/\1/p' /tmp/dependencies) /target/davmail/lib/
RUN mv -v /davmail-code/target/davmail-*.jar /target/davmail/
RUN cd /target/davmail && ln -s davmail-*.jar davmail.jar

FROM ${BASE_IMAGE}

RUN apk add --update --no-cache openssl

COPY --from=builder /target /

ENTRYPOINT java $JAVA_OPTS -cp /davmail/davmail.jar:/davmail/lib/* davmail.DavGateway -notray -server /etc/davmail.properties

# TODO https://github.com/moby/moby/issues/45897#issuecomment-1656345371
#   --start-interval=1s \
HEALTHCHECK \
  --interval=5s \
  --start-period=5s \
  CMD echo "" | openssl s_client -connect localhost:993 | grep -E $'\* OK .* server ready\r$' || exit 1
