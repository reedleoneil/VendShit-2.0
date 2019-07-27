class Vendo {
	constructor() {	
		var vendo = this;
		this.credit = 0;
		this.onCredit = null;
		this.client = new Paho.Client("localhost", Number("1884"), "", "");

		vendo.client.onConnectionLost = onConnectionLost;
		vendo.client.onMessageArrived = onMessageArrived;
		vendo.client.connect({onSuccess:onConnect});

		function onConnect() {
			console.log("onConnect");
			vendo.client.subscribe("vendo/credit");
		};

		function onConnectionLost(responseObject) {
			if (responseObject.errorCode !== 0)
				console.log("onConnectionLost:"+responseObject.errorMessage);
		};

		function onMessageArrived(message) {
			console.log("onMessageArrived:"+message.payloadString);
			vendo.credit = message.payloadString;
			if (vendo.onCredit !== null)
				vendo.onCredit(vendo.credit);
		};
	}

	vend(slot, price) {
		this.credit = this.credit - price;
		if (this.onCredit !== null)
			this.onCredit(this.credit);

		for (var r = this.credit; r < this.credit + price; r++) {
			var message = new Paho.Message("e");
			message.destinationName = "vendo/commands";
			this.client.send(message);
		} 

		var message = new Paho.Message("1");
		message.destinationName = "vendo/commands";
		this.client.send(message);
	}
}


