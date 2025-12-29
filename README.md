# SignSpeak Smart Glove

A wearable assistive device that translates sign language gestures into natural spoken sentences in real-time.

## Project Structure

```
Project_fsociety/
├── firmware/              # ESP32 Arduino code
│   ├── signspeak_glove.ino
│   └── libraries.txt
├── python_app/            # Python application
│   ├── main.py           # Main application pipeline
│   ├── data_receiver.py  # Bluetooth serial receiver
│   ├── preprocessor.py   # Data normalization
│   ├── gesture_classifier.py  # Random Forest model
│   ├── gemini_integration.py   # Google Gemini API
│   ├── tts_handler.py    # Text-to-Speech
│   └── config.py         # Configuration settings
├── data/                  # Training data storage
├── models/                # Saved ML models
├── requirements.txt       # Python dependencies
└── README.md
```

## Hardware Requirements

- ESP32 Development Board
- 5x Flex Sensors (analog)
- MPU6050 IMU (I2C)
- 1200mAh Li-Ion Battery
- Battery Charging Module
- Resistors for flex sensors (10kΩ pull-down recommended)

## Software Requirements

- Python 3.8+
- Arduino IDE with ESP32 board support
- Google AI Studio API key (for Gemini)
- Internet connection (for Gemini and TTS)

## Setup Instructions

### 1. Hardware Setup

1. Connect 5 flex sensors to ESP32 analog pins (A0-A4)
2. Connect MPU6050 to ESP32 I2C pins (SDA, SCL)
3. Connect battery and charging module
4. Upload firmware from `firmware/signspeak_glove.ino`

### 2. Software Setup

```bash
# Install Python dependencies
pip install -r requirements.txt

# Configure API keys
# Edit python_app/config.py and add your Google AI Studio API key
```

### 3. Training the Model

```bash
# Collect training data (run data collection script)
python python_app/collect_training_data.py

# Train the model
python python_app/train_model.py
```

### 4. Running the Application

```bash
python python_app/main.py
```

## Features

- Real-time gesture recognition (20Hz sampling)
- Context-aware sentence generation using Google Gemini
- Natural speech output using Google TTS
- Low latency (<500ms end-to-end)
- Privacy-first (no cameras)

## Performance Metrics

- Target Accuracy: >85% gesture classification
- Latency: <500ms end-to-end
- Battery Life: 6-8 hours continuous operation
- Range: Up to 10 meters Bluetooth range

## Future Enhancements

- On-device AI with TensorFlow Lite
- Bilateral communication with OLED display
- Mobile app (Flutter)

## License

This project is developed for assistive technology purposes.

