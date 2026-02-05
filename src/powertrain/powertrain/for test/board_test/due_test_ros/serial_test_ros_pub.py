#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32
import time

class SerialTestPublisher(Node):
    def __init__(self):
        super().__init__('pub_test')
        self.publisher_ = self.create_publisher(Int32, '/serial_test', 10)
        self.timer = self.create_timer(1.0, self.timer_callback)  # 1초마다
        self.count = 0

    def timer_callback(self):
        msg = Int32()
        msg.data = self.count
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publishing: {self.count}')
        self.count += 1
        if self.count > 100:
            self.count = 0

def main(args=None):
    rclpy.init(args=args)
    node = SerialTestPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
