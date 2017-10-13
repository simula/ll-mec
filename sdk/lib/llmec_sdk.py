'''
   The MIT License (MIT)

   Copyright (c) 2017

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
   
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
'''

'''
    File name: llmec_sdk.py
    Author: navid nikaein
    Description: Library to get and set accessible paramters and operation through the llmec
    version: 1.0
    Date created: 7 July 2017
    Date last modified: 7 July 2017 
    Python Version: 2.7
'''

import json
# Make it work for Python 2+3 and with Unicode
import io
import requests
import time
import logging
import argparse
import os
import pprint
import yaml

from logger import *

from enum import Enum


class rrc_triggers(Enum):

    ONE_SHOT = 0
    PERIODIC = 1
    EVENT_DRIVEN= 2

class cd_actions(Enum):

    PULL = 0
    PUSH = 1
    
    #def describe(self):
        #return self.name, self.value

    #def __str__(self):
        #return '%s' % self._value_

class llmec_rest_api(object):

    # policy file
    fs_all='outputs/stats_flow.json'

    # APIs 
    add_ue='/ue'

    redirect_ue='/ue/redirect'

    flow_flush='/flow/flush'

    flow_stats='/stats/flow'

class ue_manager(object):
    def __init__(self, log, url='http://localhost', port='9999', op_mode='test'):
        super(ue_manager, self).__init__()
        
        self.url = url+':'+port
        self.status = ''
        self.op_mode = op_mode
        self.log = log

        self.add_ue_api=llmec_rest_api.add_ue
        self.redict_ue_api=llmec_rest_api.redirect_ue

       
    # data: {"s1_ul_teid":"0x01", "s1_dl_teid":"0x8d3ded37","ue_ip":"172.16.0.2","enb_ip":"192.168.12.79"}

    def add_ue_rule(self, ul_teid='0x01', dl_teid='0x8d3ded37',ue_ip='172.16.0.2',enb_ip='192.168.12.79'):

        url = self.url+self.add_ue_api 
        data= {'s1_ul_teid': ul_teid, 's1_dl_teid' : dl_teid, 'ue_ip': ue_ip, 'enb_ip' : enb_ip}

        if self.op_mode == 'test' :
            self.log.info('POST ' + str(url))
            self.log.info('Data ' + str(data))

        elif self.op_mode == 'sdk' : 
            try :
                self.log.debug('POST ' + str(url))
                self.log.debug('Data ' + str(data))
                req = requests.post(url,json.dumps(data),headers={'Content-Type': 'application/x-www-form-urlencoded'})
                if req.status_code == 200 :
                    self.log.error('successfully added a UE specific rule' )
                    self.status='connected'
                else :
                    self.status='disconnected'
                self.log.error('Request error code : ' + req.status_code)
            except :
                self.log.error('Failed to add a UE specific rule' )

        else :
            self.log.warn('Unknown operation mode ' + op_mode )       

    def redirect_ue_rule(self, ul_teid='0x01', dl_teid='0x8d3ded37',ue_ip='172.16.0.2',enb_id='192.168.12.79', remote_ip='193.55.113.118', local_ip=''):

        url = self.url+self.redirect_ue_api 
        data= {'s1_ul_teid': ul_teid, 's1_dl_teid' : dl_teid, 'ue_ip': ue_ip, 'enb_ip' : enb_ip,'from':remote_ip, 'to': local_ip}
        
        if self.op_mode == 'test' :
            self.log.info('POST ' + str(url))
            self.log.info('Data ' + str(data))

        elif self.op_mode == 'sdk' : 
            try :
                self.log.debug('POST ' + str(url))
                self.log.debug('POST ' + str(url))
                self.log.debug('Data ' + str(data))
               
                req = requests.post(url,json.dumps(data),headers={'Content-Type': 'application/x-www-form-urlencoded'})
                if req.status_code == 200 :
                    self.log.error('successfully added a UE specific redirection rule' )
                    self.status='connected'
                else :
                    self.status='disconnected'
                self.log.error('Request error code : ' + req.status_code)
            except :
                self.log.error('Failed to add a UE redirection rule' )

        else :
            self.log.warn('Unknown operation mode ' + op_mode )       

            

class flow_manager(object):
    def __init__(self, log, url='http://localhost', port='9999', op_mode='test'):
        super(flow_manager, self).__init__()

        self.url = url+':'+port
        self.status = ''
        self.op_mode = op_mode
        self.log = log
        self.stats_data = ''

        self.flow_flush=llmec_rest_api.flow_flush
        self.flow_stats=llmec_rest_api.flow_stats
       
        self.fs_file = llmec_rest_api.fs_all
 
    def flow_flush(self):
       
        url = self.url+self.flow_flush

        if self.op_mode == 'test' :
            self.log.info('POST ' + str(url))

        elif self.op_mode == 'sdk' : 
            try :
                req = requests.post(url)
                if req.status_code == 200 :
                    self.log.error('successfully flushed the rules ' )
                    self.status='connected'
                else :
                    self.status='disconnected'
                self.log.error('Request error code : ' + req.status_code)
            except :
                self.log.error('Failed to delegate the DL schedling to the agent' )

        else :
            self.log.warn('Unknown operation mode ' + op_mode )                 
        
 
    def flow_status(self):
       
        url = self.url+self.flow_stats
        self.log.debug('POST ' + str(url))
        
        file = ''

        if self.op_mode == 'test' :
            
            file =  self.fs_file
            
            try:
                with open(file) as data_file:
                    self.stats_data = json.load(data_file)
                    self.status='connected'
            except :
                self.status='disconnected'
                self.log.error('cannot find the output file'  + file )       


        elif self.op_mode == 'sdk' : 
            try :
                req = requests.get(url)
                if req.status_code == 200 :
                    self.stats_data = req.json()
                    self.log.debug('successfully got the flow status ' )
                    self.status='connected'
                else :
                    self.status='disconnected'
                self.log.error('Request error code : ' + req.status_code)
            except :
                self.log.error('Failed to get the flow status' )

        else :
            self.log.warn('Unknown operation mode ' + op_mode )                 

        if self.status == 'connected' :     
            self.log.debug('Flow Stats Manager requested data')
            self.log.debug(json.dumps(self.stats_data, indent=2))

            
    def get_num_rules(self):
        return len(self.stats_data)
        
    def get_num_ues(self):
        return self.get_num_rules()/2

    def get_num_bytes(self, ue_id=0, dir='UL'):
        index=0
        flow_dir='upstream'
        if dir == 'dl' or dir == 'DL' :
            index=2*ue_id + 1
            flow_dir='downstream'
        if dir == 'ul' or dir == 'UL' :
            index=2*ue_id

        self.log.info('UE id ' + str(ue_id) + ' in ' + flow_dir + ' byte count: ' + str(self.stats_data[index]['byte_count']))    

        return self.stats_data[index]['byte_count']

    def get_num_packets(self, ue_id=0, dir='UL'):
        index=0
        flow_dir='upstream'
        if dir == 'dl' or dir == 'DL' :
            index=2*ue_id + 1
            flow_dir='downstream'
        if dir == 'ul' or dir == 'UL' :
            index=2*ue_id
            
        self.log.info('UE id ' + str(ue_id) + ' in ' + flow_dir + ' packet count: ' + str(self.stats_data[index]['packet_count']))    
        return self.stats_data[index]['packet_count']

    def get_flow_life_time(self, ue_id=0, dir='UL'):
        index=0
        flow_dir='upstream'
        if dir == 'dl' or dir == 'DL' :
            index=2*ue_id + 1
            flow_dir='downstream'
        if dir == 'ul' or dir == 'UL' :
            index=2*ue_id
            
        self.log.info('UE id ' + str(ue_id) + ' in ' + flow_dir + ' flow lifetime: ' + str(self.stats_data[index]['duration_sec']))    
        return self.stats_data[index]['duration_sec']

    def get_flow_priority(self, ue_id=0, dir='UL'):
        index=0
        flow_dir='upstream'
        if dir == 'dl' or dir == 'DL' :
            index=2*ue_id + 1
            flow_dir='downstream'
        if dir == 'ul' or dir == 'UL' :
            index=2*ue_id

        self.log.info('UE id ' + str(ue_id) + ' in ' + flow_dir + ' flow priority: ' + str(self.stats_data[index]['priority']))    
        return self.stats_data[index]['priority']

    def get_flow_in_port(self, ue_id=0, dir='UL'):
        index=0
        flow_dir='upstream'
        if dir == 'dl' or dir == 'DL' :
            index=2*ue_id + 1
            flow_dir='downstream'
        if dir == 'ul' or dir == 'UL' :
            index=2*ue_id

        return self.stats_data[index]['in_port']

    def get_flow_table_id(self, ue_id=0, dir='UL'):
        index=0
        flow_dir='upstream'
        if dir == 'dl' or dir == 'DL' :
            index=2*ue_id + 1
            flow_dir='downstream'
        if dir == 'ul' or dir == 'UL' :
            index=2*ue_id

        return self.stats_data[index]['flow_table_id']

