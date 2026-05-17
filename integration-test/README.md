# Getting Started

Run all of these commands on a 5B. Make sure swclk is connected to pin 24 and swdio is connected to 25

``` bash
# Install the arduino cli 
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh # Add the binary to your path

# setup packages for openocd
sudo apt update -y && sudo apt install -y git make pkg-config autoconf libtool libusb-1.0-0-dev libhidapi-dev gcc g++ libgpiod-dev libjim-dev

# clone openocd and build
git clone https://github.com/raspberrypi/openocd.git --branch rpi-common --depth=1
cd openocd
./bootstrap
./configure --enable-linuxgpiod --disable-werror
sudo make -j4
sudo make install 

# Run openocd to verify the Pico can be reached
sudo openocd -f rpi-swd.cfg -f target/rp2040.cfg -c "adapter speed 100" -c "init" -c "targets" -c "exit" 2>&1

# Setup Arduino CLI for the RP2040
arduino-cli core update-index
arduino-cli config add board_manager.additional_urls \
  https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
arduino-cli core update-index
arduino-cli core install rp2040:rp2040

# Setup and build binary
cd ~/
arduino-cli sketch new Blink
cd Blink

cat > Blink.ino << 'EOF'
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
EOF

arduino-cli compile -b rp2040:rp2040:rpipico Blink --output-dir=.

# Setup config
cat > rpi-swd.cfg << 'EOF'
adapter driver linuxgpiod
transport select swd
adapter gpio swclk 24 -chip 4
adapter gpio swdio 25 -chip 4
adapter speed 1000
EOF

# Program Binary
sudo openocd -f rpi-swd.cfg -f target/rp2040.cfg -c "program Blink.ino.elf verify reset exit"
```
