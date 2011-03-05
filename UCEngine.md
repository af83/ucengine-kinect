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


Ruby
----

http://docs.ucengine.org/ruby_install.html
 -> les exemples ne marchent pas => pas testé
 -> le port UCEngine.new devrait avoir une valeur par défaut : 80 ?
 -> quel intérêt de faire un yield self sur connect ?
 -> quand `connect` échoue, une exception est levée, pas terrible, ça devrait au moins être documenté
 -> certains exemples de `connect` utilisent :credential et d'autres :password
 -> il est marqué que `:parent` est obligatoire pour `publish` mais l'exemple ne le met pas
 -> utiliser des symboles plutôt que des constantes pour les niveaux de logs

Javascript
----------

Create presence
 -> le credential/password est avant le uid, alors que c'est l'inverse en Ruby

Attach presence
 -> l'exemple ne marche pas : un paramètre en trop sur uce.presence.create ?

startLoop
 -> pas documenté
 -> expliquer `meeting.startLoop((new Date()).getTime());`

