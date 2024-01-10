FROM ruby:3.2-alpine

RUN apk add --update --no-cache libffi-dev

RUN gem install imap-backup

ENTRYPOINT ["imap-backup"]
