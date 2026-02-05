from setuptools import setup
import os
from glob import glob

package_name = 'due_test_ros'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name), glob('*.py')),
    ],
    install_requires=['setuptools', 'pyserial'],
    zip_safe=True,
    maintainer='dcubot',
    maintainer_email='dcubot@example.com',
    description='ROS2 nodes for Arduino DUE serial test',
    license='Apache License 2.0',
    entry_points={
        'console_scripts': [
            'pub_test = serial_test_due_ros_pub:main',
            'sub_test = serial_test_due_ros_sub_wrt:main',
        ],
    },
)
