/*
Licence: GPLv3
todo: improve ugly function set_ip_first()
*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

using namespace std;
int main()
{
	char network[40];
	char buffer[40];
	int number_subnets;
	subnet* sn = NULL; // pointer to sn
	cout<<"Input your Network in format [w.x.y.z/a]: ";
	cin>>network;
	//count_subnets = atoi(buffer);
	subnet  vlsm = subnet(network); // vlms = big network, which will be divided
	cout<< vlsm.print_net();
	do
	{
		cout<<"Enter number of subnets: ";
		cin>>buffer;
		number_subnets = atoi(buffer);
	} while(number_subnets <= 0);
	
	sn = new subnet[number_subnets](); // generate subnets

	for(int i=0; i<number_subnets; i++)
	{
		int number_hosts;
		int number_hosts_subnet = 0;
		do
		{
			cout<<"Enter number of hosts for subnet "<<i<<": ";
			cin>>buffer;
			number_hosts = atoi(buffer);

		} while (number_hosts <= 0);

		for(int j=0; number_hosts+2 > number_hosts_subnet; j++)
		{
			number_hosts_subnet = 1 << j;
		} //for
		sn[i].set_hosts(number_hosts_subnet);
		sn[i].calc_netmask();
		} //for

	sort_nets(sn, number_subnets); // sort subnets
	
	sn[0].set_ip_first(add_ip(vlsm.get_ip_first(), 1));
	sn[0].set_ip_last(add_ip(sn[0].get_ip_first(), sn[0].get_hosts()-1));
	
	//sn[1].set_ip_first(add_ip(sn[0].get_ip_last(), 1));

	for(int i=1; i<number_subnets; i++)
	{
		sn[i].set_ip_first(add_ip(sn[i-1].get_ip_last(), 1));
		sn[i].set_ip_last(add_ip(sn[i].get_ip_first(), sn[i].get_hosts()-1));
	}

	cout<<endl;
	for(int i=0; i<number_subnets; i++)
	{
		cout<<"---- Subnet "<<i<<" ----\n";
		cout<<sn[i].print_net();
	}
} //main
