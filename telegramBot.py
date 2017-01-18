# -*- coding: utf-8 -*-

import telebot # Librería de la API del bot.
from telebot import types # Tipos para la API del bot.
import time # Librería para hacer que el programa que controla el bot no se acabe.
import sys


import httplib2
h = httplib2.Http(".cache")
(resp_headers, content) = h.request("http://192.168.1.34/ledOFF", "GET")


reload(sys)
sys.setdefaultencoding("utf-8") #evitar problemas de codificación

TOKEN = '******' # Nuestro tokken del bot (el que @BotFather nos dió).
bot = telebot.TeleBot(TOKEN) # Creamos el objeto de nuestro bot.

def listener(messages):
    for m in messages:
        cid = m.chat.id
        if cid > 0:
            print str(m.chat.first_name) + " [" + str(cid) + "]: " + m.text # Si 'cid' es positivo, usaremos 'm.chat.first_name' para el nombre
        else:
            print str(m.from_user.first_name) + "[" + str(cid) + "]: " + m.text # Si 'cid' es negativo, usaremos 'm.from_user.first_name' para el nombre

        text = m.text
        if text:
            words = text.split()

            for i, word in enumerate(words):
                # Process commands:
                if word == '/ledON':
                    ledON(bot,cid)
                elif word == '/ledOFF':
                    ledOFF(bot,cid)
                    break
def ledON(bot,cid):
    (resp_headers, content) = h.request("http://192.168.1.34/ledON", "GET")
    bot.send_message(cid, content)
    print content

def ledOFF(bot,cid):
    (resp_headers, content) = h.request("http://192.168.1.34/ledOFF", "GET")
    bot.send_message(cid, content)
    print content


bot.set_update_listener(listener) # Así, le decimos al bot que utilice como función escuchadora nuestra función 'listener' declarada arriba.

bot.polling(none_stop=True) # Con esto, le decimos al bot que siga funcionando incluso si encuentra algún fallo.
