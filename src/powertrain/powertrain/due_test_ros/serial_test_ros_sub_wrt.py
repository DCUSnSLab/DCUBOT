#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32
import serial
import time

class SerialTestSubscriber(Node):
    def __init__(self):
        super().__init__('sub_test')
        self.subscription = self.create_subscription(
            Int32,
            '/serial_test',
            self.listener_callback,
            10)
        self.subscription  # prevent unused warning
        # 시리얼 포트 설정
        self.ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        time.sleep(2)  # 연결 안정화

    def listener_callback(self, msg):
        self.get_logger().info(f'Received: {msg.data}')
        self.ser.write(f'{msg.data}\n'.encode())  # 1초 간격은 퍼블리셔와 맞춰짐

def main(args=None):
    rclpy.init(args=args)
    node = SerialTestSubscriber()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.ser.close()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
