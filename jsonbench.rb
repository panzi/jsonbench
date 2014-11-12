#!/usr/bin/ruby

require 'json'

def main
	repeat   = ARGV[0].to_i
	filename = ARGV[1]
	buf      = File.read(filename)
	duration = 0

	for _ in 0...repeat
		start = Time.now
		JSON.parse(buf)
		duration += Time.now - start
	end

	puts (duration * 1000).to_i
end

main if __FILE__ == $0
