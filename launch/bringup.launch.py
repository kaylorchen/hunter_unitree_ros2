from launch import LaunchDescription
from launch.conditions import (
    LaunchConfigurationEquals,
    LaunchConfigurationNotEquals,
    IfCondition,
)
from launch_ros.actions import Node
from launch.actions import (
    IncludeLaunchDescription,
    DeclareLaunchArgument,
    GroupAction,
    TimerAction,
)
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution, Command


def generate_launch_description():
    use_sim_time = LaunchConfiguration("use_sim_time")
    # Declare launch options
    declare_use_sim_time_cmd = DeclareLaunchArgument(
        "use_sim_time",
        default_value="False",
        description="Use simulation (Gazebo) clock if true",
    )
    bringup_hunter_tf_pub = GroupAction(
        actions=[
            Node(
                package="hunter_unitree_ros2",
                executable="hunter_unitree_ros2_node",
                output="screen",
                parameters=[
                    {"use_sim_time": use_sim_time},
                    {"wait_for_standup": 3},
                ],
                arguments=["--ros-args", "--log-level", "info"],
            ),
        ]
    )
    ld = LaunchDescription()
    ld.add_action(declare_use_sim_time_cmd)
    ld.add_action(bringup_hunter_tf_pub)
    return ld
