
# Binary Installation
## Add Software Source
```bash
cat << 'EOF' | sudo tee /etc/apt/sources.list.d/kaylordut.list
deb [signed-by=/etc/apt/keyrings/kaylor-keyring.gpg] http://apt.kaylordut.cn/kaylordut/ kaylordut main
EOF
cat << 'EOF' | sudo tee /etc/apt/preferences.d/kaylordut
Package: *
Pin: release o=kaylordut kaylordut,a=kaylordut,n=kaylordut,l=kaylordut kaylordut,c=main,b=arm64
Pin-Priority: 1099
EOF
sudo mkdir /etc/apt/keyrings -pv
sudo wget -O /etc/apt/keyrings/kaylor-keyring.gpg http://apt.kaylordut.cn/kaylor-keyring.gpg
sudo apt update
```
## Install Package for Unitree Go2 Robot
```bash
sudo apt install -y ros-humble-hunter-unitree-ros2
```

# Source Installation
## Install Unitree API
```bash
mkdir ~/unitree_ws -pv
cd ~/unitree_ws
git clone https://github.com/unitreerobotics/unitree_ros2.git 
git checkout v0.3.0
cd unitree_ros2/cyclonedds_ws/src/unitree
colcon build --event-handlers console_direct+ --build-base build_pc --install-base install_pc --continue-on-error --packages-select unitree_api
source install_pc/setup.zsh # or source install_pc/setup.bash if your shell is bash
```
## Install Unitree Go2 Robot
```bash
cd ~/unitree_ws
git clone https://github.com/kaylorchen/hunter_unitree_ros2.git
cd hunter_unitree_ros2
colcon build --event-handlers console_direct+ --build-base build_pc --install-base install_pc --continue-on-error --packages-select hunter_unitree_ros2
source install_pc/setup.zsh # or source install_pc/setup.bash if your shell is bash
```


