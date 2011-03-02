Notes sur UCEngine
==================

Intro
-----

Objectif : écrire une application JS qui utilise UCEngine

François a installé un serveur UCE pour moi sur 192.168.1.48


Site web
--------

http://docs.ucengine.org/ucejs.html :

- n'explique pas où on peut récupérer la lib JS
- ne dit pas de quelles libs JS il dépend
- comment on se connecte à un serveur UCE ?
  -> réponse de François : pour le moment, ne marche qu'en local


API
---

curl http://192.168.1.48/api/0.3/infos
 -> renvoie une erreur 404, pourquoi ? mauvais port et mauvais host

curl -H "Host: nono.localhost" http://192.168.1.48:5280/api/0.3/infos

