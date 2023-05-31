#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>

static struct nf_hook_ops nfho;

// Hàm hook được gọi khi gói tin đi qua hook
unsigned int modify_packet(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    struct iphdr *ip_header;
    struct tcphdr *tcp_header;
    char *payload;

    // Kiểm tra xem gói tin có phải là gói tin TCP không
    if (skb->protocol == htons(ETH_P_IP))
    {
        ip_header = ip_hdr(skb);
        if (ip_header->protocol == IPPROTO_TCP)
        {
            tcp_header = tcp_hdr(skb);
            payload = (char *)(skb->data + sizeof(struct iphdr) + sizeof(struct tcphdr));

            // Kiểm tra xem payload có phải là "hello" không và thay đổi thành "goodbye"
            if (memcmp(payload, "hello", 5) == 0)
            {
                memcpy(payload, "goodbye", 7);
            }
        }
    }

    return NF_ACCEPT; // Chấp nhận gói tin và cho phép nó tiếp tục đi qua hook
}

// Hàm khởi tạo module
static int __init hello_init(void)
{
    nfho.hook = modify_packet;                   // Hàm hook để thay đổi gói tin
    nfho.hooknum = NF_INET_POST_ROUTING;          // Hook POST_ROUTING
    nfho.pf = PF_INET;                            // Áp dụng cho giao thức IPv4
    nfho.priority = NF_IP_PRI_FIRST;              // Độ ưu tiên của hook

    nf_register_net_hook(&init_net, &nfho);       // Đăng ký hook

    return 0;
}

// Hàm kết thúc module
static void __exit hello_exit(void)
{
    nf_unregister_net_hook(&init_net, &nfho);     // Hủy đăng ký hook
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
