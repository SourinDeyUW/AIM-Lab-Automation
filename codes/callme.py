#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd
import numpy as np
import csv
import random

def capture(on,i):
    df=pd.read_csv('data.csv')
    f=random.randint(2,100)
    #print(f)
    df['ratio'].replace('  ', np.nan, inplace=True)
    df2=df.dropna(subset=['ratio'])
    a=df2['ratio'].shape 
    df.at[a[0],'ratio']=f
    df.to_csv('data.csv', index=False)


# In[ ]:




