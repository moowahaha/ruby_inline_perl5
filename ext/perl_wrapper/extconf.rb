require 'mkmf'

$CFLAGS = `perl -MExtUtils::Embed -e ccopts -e ldopts`.gsub(/\s+/, ' ').strip

create_makefile("perl_wrapper")
