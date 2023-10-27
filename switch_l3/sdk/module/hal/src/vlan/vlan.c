#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/genetlink.h>
#include <net/genetlink.h>

#include "vlan.h"
#include "vlan_share.h"

static int doVlanCommand(struct sk_buff *skb, struct genl_info *info)
{
    int		ret = 0;
	void	       *hdr;
	struct sk_buff *msg;
    int cmd = -1;

	/* Check if the attribute is present and print it */
	if (info->attrs[GENLTEST_VLAN_CMD]) {
		cmd = nla_get_u32(info->attrs[GENLTEST_A_MSG]);
		pr_info("vlan: cmd = %d\n", cmd);
	} else {
		pr_info("empty message received\n");
	}
    switch (cmd)
    {
    case SDK_VLAN_SET:
        printk("Do Set VLAN")
        break;
    case SDK_VLAN_GET:
        printk("Do Get VLAN")
        break;
    
    default:
        break;
    }
	/* Allocate a new buffer for the reply */
	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		pr_err("failed to allocate message buffer\n");
		return -ENOMEM;
	}


	/* Put the Generic Netlink header */
	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq, &genl_fam, 0,
			  GENLTEST_CMD_VLAN);
	if (!hdr) {
		pr_err("failed to create genetlink header\n");
		nlmsg_free(msg);
		return -EMSGSIZE;
	}
	/* And the message */
	if ((ret = nla_put_u32(msg, GENLTEST_VLAN_RET,
				  1))) {
		pr_err("failed to create message string\n");
		genlmsg_cancel(msg, hdr);
		nlmsg_free(msg);
		goto out;
	}

	/* Finalize the message and send it */
	genlmsg_end(msg, hdr);

	ret = genlmsg_reply(msg, info);
	pr_info("reply sent\n");


out:
	return ret;
}