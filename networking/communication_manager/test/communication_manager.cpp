#include <gtest/gtest.h>

extern "C" {
#include <buracchi/common/networking/communication_manager.h>
#include <buracchi/common/networking/nproto/nproto_service_ipv4.h>
#include <buracchi/common/networking/tproto/tproto_service_tcp.h>
}

#include <cstdint>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

static void foo(cmn_socket2_t socket, std::atomic<int> &counter);

constexpr int request_number = 1024;

TEST(cmn_communication_manager, test) {
	std::atomic<int> counter(0);
	cmn_communication_manager_t cm;
	cm = cmn_communication_manager_init(8);
	std::thread server([&cm, &counter] {
		cmn_communication_manager_start(cm, "0.0.0.0:1234", reinterpret_cast<void (*)(cmn_socket2_t, void*)>(&foo), &counter);
	});
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::vector<std::thread> clients;
	clients.reserve(request_number);
	for (int i = 0; i < request_number; i++) {
		clients.emplace_back([] {
			bool msg_received;
			uint8_t buff;
			cmn_socket2_t socket;
			msg_received = false;
			while (!msg_received) {
				if (socket = cmn_socket2_init(cmn_nproto_service_ipv4, cmn_tproto_service_tcp)) {
					if (cmn_socket2_connect(socket, "127.0.0.1:1234") == -1) {
						cmn_socket2_destroy(socket);
						continue;
					}
					if (cmn_socket2_recv(socket, &buff, 1) == -1) {
						cmn_socket2_destroy(socket);
						continue;
					}
					msg_received = true;
					cmn_socket2_destroy(socket);
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
		});
	}
	std::for_each(clients.begin(), clients.end(), [](std::thread &client) {
		client.join();
	});
	cmn_communication_manager_stop(cm);
	server.join();
	cmn_communication_manager_destroy(cm);
	ASSERT_EQ(counter, request_number);
}

static void foo(cmn_socket2_t socket, std::atomic<int> &counter) {
	uint8_t buff = 1;
	if (socket) {
		cmn_socket2_send(socket, &buff, 1);
		counter++;
	}
}
