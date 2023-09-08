#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/genetlink.h>
#include <net/genetlink.h>

#include "../my_gen_netlink.h"

/* Handler for GENLTEST_CMD_ECHO messages received */
static int echo_doit(struct sk_buff *skb, struct genl_info *info);
static int echo_ping(const char *buf);

/* Operations for our Generic Netlink family */
static struct genl_ops genl_ops[] = {
	{
		.cmd	= GENLTEST_CMD_ECHO,
		.doit	= echo_doit,
	 },
};

/* Multicast groups for our family */
static const struct genl_multicast_group genl_mcgrps[] = {
	{ .name = GENLTEST_MC_GRP_NAME },
};

/* Generic Netlink family */
static struct genl_family genl_fam = {
	.name	  = GENLTEST_GENL_NAME,
	.version  = GENLTEST_GENL_VERSION,
	.maxattr  = GENLTEST_A_MAX,
	.ops	  = genl_ops,
	.n_ops	  = ARRAY_SIZE(genl_ops),
	.mcgrps	  = genl_mcgrps,
	.n_mcgrps = ARRAY_SIZE(genl_mcgrps),
};

static int echo_doit(struct sk_buff *skb, struct genl_info *info)
{
	int		ret = 0;
	void	       *hdr;
	struct sk_buff *msg;

	/* Check if the attribute is present and print it */
	if (info->attrs[GENLTEST_A_MSG]) {
		char *str = nla_data(info->attrs[GENLTEST_A_MSG]);
		pr_info("message received: %s\n", str);
	} else {
		pr_info("empty message received\n");
	}

	/* Allocate a new buffer for the reply */
	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		pr_err("failed to allocate message buffer\n");
		return -ENOMEM;
	}

	/* Put the Generic Netlink header */
	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq, &genl_fam, 0,
			  GENLTEST_CMD_ECHO);
	if (!hdr) {
		pr_err("failed to create genetlink header\n");
		nlmsg_free(msg);
		return -EMSGSIZE;
	}
	/* And the message */
	if ((ret = nla_put_string(msg, GENLTEST_A_MSG,
				  "Hello from Kernel Space, Netlink!"))) {
		pr_err("failed to create message string\n");
		genlmsg_cancel(msg, hdr);
		nlmsg_free(msg);
		goto out;
	}

	/* Finalize the message and send it */
	genlmsg_end(msg, hdr);

	ret = genlmsg_reply(msg, info);
	pr_info("reply sent\n");

	echo_ping("Sangco");

out:
	return ret;
}

/* Multicast ping message to our genl multicast group */
static int echo_ping(const char *buf)
{
	int		ret = 0;
	void	       *hdr;
	/* Allocate message buffer */
	struct sk_buff *skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);

	if (unlikely(!skb)) {
		pr_err("failed to allocate memory for genl message\n");
		return -ENOMEM;
	}

	/* Put the Generic Netlink header */
	hdr = genlmsg_put(skb, 0, 0, &genl_fam, 0, GENLTEST_CMD_ECHO);
	if (unlikely(!hdr)) {
		pr_err("failed to allocate memory for genl header\n");
		nlmsg_free(skb);
		return -ENOMEM;
	}

	/* And the message */
	if ((ret = nla_put_string(skb, GENLTEST_A_MSG, buf))) {
		pr_err("unable to create message string\n");
		genlmsg_cancel(skb, hdr);
		nlmsg_free(skb);
		return ret;
	}

	/* Finalize the message */
	genlmsg_end(skb, hdr);

	/* Send it over multicast to the 0-th mc group in our array. */
	ret = genlmsg_multicast(&genl_fam, skb, 0, 0, GFP_KERNEL);
	if (ret == -ESRCH) {
		pr_warn("multicast message sent, but nobody was listening...\n");
	} else if (ret) {
		pr_err("failed to send multicast genl message\n");
	} else {
		pr_info("multicast message sent\n");
	}

	return ret;
}

static int __init init_nlexample(void)
{
    int ret = -EINVAL;

    ret = genl_register_family(&genl_fam);
    if (unlikely(ret)) {
        pr_crit("failed to register generic netlink family\n");
    }
    return ret;
}

static void __exit exit_nlexample(void)
{
    if (unlikely(genl_unregister_family(&genl_fam))) {
        pr_err("failed to unregister generic netlink family\n");
    }
}

module_init(init_nlexample);
module_exit(exit_nlexample);