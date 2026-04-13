#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class SimpleSubscriber : public rclcpp::Node {
    public:
        SimpleSubscriber() : Node("simple_subscriber") {
            sub_ = create_subscription<std_msgs::msg::String>("chatter", 10, std::bind(&SimpleSubscriber::msg_callback, this, std::placeholders::_1));
        }

        void msg_callback(const std_msgs::msg::String &msg) const {
            RCLCPP_INFO_STREAM(get_logger(), "Received: " << msg.data.c_str());
        }

    private:
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}