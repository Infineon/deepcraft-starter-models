# Snore Detection
Snoring is a prevalent issue affecting most people, often leading to disrupted sleep and potential health concerns. 

This project aims to develop an AI-driven snore detection algorithm capable of distinguishing between snorers and non-snorers. Utilizing the PSoC 6 AI Evaluation kit, the system detects snoring events, and transmits anonymized audio data to the cloud for analysis. This facilitates the continuous improvement of the machine learning model, ultimately contributing to better sleep quality and health outcomes

# Guidelines for Collecting the Data
- Power the kit through the USB connector KP3-USB
- Using you phone/PC connect to the Wi-Fi network called SNORE_SSID with password SNORE_PWD
- Using a web browser go to http://192.168.0.2:80
- Click on Scan WiFi Networks
- On the next page enter you WiFi SSID and password, snoring status and then submit
- The kit will take a few seconds to connect to the new W-Fi and reboot. You will get a connection successful on your browser
- Press SW12 to start and stop audio recording
- Snore away!

# Sensor Settings Specifications

After the connection to the server, wait for user button input (indicatied by led blink at low frequency)
- After pressing the user button, LED will become constant (indicating that the mic is on).This basically starts recording the audio data and sending it as per the configured time intervals.
- Pressing the user button again will turn the mic off and also the sending, indicated by LED OFF.
- In case there is a wifi or server disconnection, LED will start blinking at a high frequency.

# Recommended Path to Production
- Evaluate the model using a separate validation dataset to assess performance metrics such as accuracy, precision, and recall.
- Deploy the model in real-world settings to monitor performance and identify potential issues.
- Refine the model based on testing feedback to enhance efficiency and accuracy.
- Ensure the system can handle increased data volumes and user numbers.
- Implement the model within the target environment, ensuring seamless integration with existing systems.
- Continuously monitor system performance.
- Update the model as needed to adapt to new data and maintain accuracy.


Testing pull request
