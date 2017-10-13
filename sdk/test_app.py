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
    File name: test_app.py
    Author: navid nikaein
    Description: This app tests the llmec_sdk lib
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

from lib import llmec_sdk 
from lib import logger 

from threading import Timer
from time import sleep

class test_app(object):
    """test test app that makes use of llmec SDK
    """

    def __init__(self, url='http://localhost',port='9999',log_level='info', op_mode='test'):
        super(test_app, self).__init__()
        
        self.url = url+port
        self.log_level = log_level
        self.status = 0
        self.op_mode = op_mode

    def run(self, fm):
        log.info('2. Reading the status of the underlying flows')

        if args.op_mode == 'test' :
            fm.flow_status()


        print 'num rules' + str (json.dumps(fm.get_num_rules(), indent=2))
        print 'num UEs :' + str (json.dumps(fm.get_num_ues(), indent=2))
    
        for ue_id in range(0, fm.get_num_ues()) :
            fm.get_num_bytes(ue_id)
            fm.get_num_bytes(ue_id,dir='dl')
            fm.get_num_packets(ue_id)
            fm.get_num_packets(ue_id,dir='dl')
        
        
        t = Timer(5, self.run,kwargs=dict(fm=fm))
        t.start()        
                  
   
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Process some integers.')
    
    parser.add_argument('--url', metavar='[option]', action='store', type=str,
                        required=False, default='http://localhost', 
                        help='set the FlexRAN RTC URL: loalhost (default)')
    parser.add_argument('--port', metavar='[option]', action='store', type=str,
                        required=False, default='9999', 
                        help='set the FlexRAN RTC port: 9999 (default)')
    parser.add_argument('--op-mode', metavar='[option]', action='store', type=str,
                        required=False, default='sdk', 
                        help='Test SDK with already generated json files: test (default), sdk')
    parser.add_argument('--log',  metavar='[level]', action='store', type=str,
                        required=False, default='info', 
                        help='set the log level: debug, info (default), warning, error, critical')
    parser.add_argument('--version', action='version', version='%(prog)s 1.0')

    args = parser.parse_args()

    app = test_app(url=args.url,
                   port=args.port,
                   log_level=args.log,
                   op_mode=args.op_mode)
    
    log=llmec_sdk.logger(log_level=args.log).init_logger()
    log.info('test')
    
    fm = llmec_sdk.flow_manager(log=log,
                                url=args.url,
                                port=args.port,
                                op_mode=args.op_mode)

    #t = Timer(5, test_app.run,kwargs=dict(fm=fm))
    #t.start()

    if args.op_mode == 'test' :
        fm.flow_status()
        

    print 'num rules' + str (json.dumps(fm.get_num_rules(), indent=2))
    print 'num UEs :' + str (json.dumps(fm.get_num_ues(), indent=2))
    
    for ue_id in range(0, fm.get_num_ues()) :
        fm.get_num_bytes(ue_id)
        fm.get_num_bytes(ue_id,dir='dl')
        fm.get_num_packets(ue_id)
        fm.get_num_packets(ue_id,dir='dl') 
    
    
   
        
