#ifndef VLAN_SHARE_H
#define VLAN_SHARE_H

typedef struct testVlan
{
    int vlanId;
    int vlanPort;
} testVlan_t;

enum sdkVlan_cmd 
{
	SDK_VLAN_SET,
	SDK_VLAN_GET,
}

enum genltestVlan_attrs {
	GENLTEST_A_UNSPEC,
	GENLTEST_VLAN_CMD,
	GENLTEST_VLAN_RET,
	GENLTEST_VLAN_STRUCT,
	GENLTEST_VLAN_ID,
	GENLTEST_VLAN_PORT,
	__GENLTEST_A_MAX,
};
#endif /*VLAN_SHARE_H */