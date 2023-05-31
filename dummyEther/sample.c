#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/init.h>

static struct net_device *dummy_dev;

static int dummy_open(struct net_device *dev)
{
    printk(KERN_INFO "Dummy Interface: Device opened\n");
    netif_start_queue(dev);
    return 0;
}

static int dummy_stop(struct net_device *dev)
{
    printk(KERN_INFO "Dummy Interface: Device closed\n");
    netif_stop_queue(dev);
    return 0;
}

static netdev_tx_t dummy_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
    printk(KERN_INFO "Dummy Interface: Transmitting packet\n");
    dev_kfree_skb(skb);
    return NETDEV_TX_OK;
}

static struct net_device_ops dummy_netdev_ops = {
    .ndo_open = dummy_open,
    .ndo_stop = dummy_stop,
    .ndo_start_xmit = dummy_start_xmit,
};

static void dummy_setup(struct net_device *dev)
{
    ether_setup(dev);
    dev->netdev_ops = &dummy_netdev_ops;
}

static int __init dummy_init(void)
{
    dummy_dev = alloc_netdev(0, "dummy%d", NET_NAME_UNKNOWN, dummy_setup);
    if (!dummy_dev)
        return -ENOMEM;

    if (register_netdev(dummy_dev)) {
        free_netdev(dummy_dev);
        return -ENODEV;
    }

    printk(KERN_INFO "Dummy Interface: Module loaded\n");
    return 0;
}

static void __exit dummy_exit(void)
{
    unregister_netdev(dummy_dev);
    free_netdev(dummy_dev);
    printk(KERN_INFO "Dummy Interface: Module unloaded\n");
}

module_init(dummy_init);
module_exit(dummy_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Dummy Interface Driver");

