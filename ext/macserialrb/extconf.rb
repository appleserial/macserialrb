require "mkmf"

case RUBY_PLATFORM
when /linux/i
  $CPPFLAGS += " -std=c11 -Wall"
when /darwin/i
  $CPPFLAGS += " -std=c11 -Wall"
end

create_makefile("macserialrb/macserialrb")
