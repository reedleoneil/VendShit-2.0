require 'rubyserial'
require 'json'
require 'paho-mqtt'

serialport = Serial.new '/dev/ttyUSB0'
client = PahoMqtt::Client.new()

client.on_message do |p|
	puts "Topic: #{p.topic}\nPayload: #{p.payload}\nQoS: #{p.qos}"
	serialport.write(p.payload)
end

client.connect('localhost', 1883, client.keep_alive, true, true)
client.subscribe(["vendo/servo", 2])

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
		payload = JSON.parse(payload)
		client.publish("vendo/credit", payload['credit'], false, 1)
	end
}

loop do
	client.loop_write
	client.loop_read
end
