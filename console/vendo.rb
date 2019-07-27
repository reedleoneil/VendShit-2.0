require 'rubyserial'
require 'json'

serialport = Serial.new '/dev/ttyUSB0'

Thread.new {
	loop do
		serialport.write 'q'
		x = ''
		payload = "{"
		while x != '{' do
			x = serialport.read 1
		end
		while x != '}' do
			x = serialport.read 1
			if x != '' then payload << x end
		end
		puts payload
	end
}

loop do

end
