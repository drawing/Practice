package main

// openssl rsa -in imsdk.pem -out pri.pem

import (
	"fmt"
	apns "github.com/anachronistic/apns"
	"os"
)

func main() {
	payload := apns.NewPayload()
	payload.Alert = "test content"
	payload.Badge = 32
	payload.Sound = "msgTritone.caf"

	feedClient := apns.NewClient("feedback.sandbox.push.apple.com:2196", "imsdk.pem", "pri.pem")
	go feedClient.ListenForFeedback()

	pn := apns.NewPushNotification()
	pn.DeviceToken = "TOKEN_ID"
	pn.AddPayload(payload)

	// test server: gateway.sandbox.push.apple.com:2195
	// prod server: gateway.push.apple.com:2195
	client := apns.NewClient("gateway.sandbox.push.apple.com:2195", "imsdk.pem", "pri.pem")
	resp := client.Send(pn)

	fmt.Println("Success:", resp.Success)
	fmt.Println("  Error:", resp.Error)

	select {
	case resp := <-apns.FeedbackChannel:
		fmt.Println("- recv'd:", resp.DeviceToken)
	case <-apns.ShutdownChannel:
		fmt.Println("- nothing returned from the feedback service")
		os.Exit(1)
	}
}
