Kinnect with UCEngine
=====================

Instructions for a quick start:

    git clone ... && cd kinnect.uce
    echo "127.0.0.1 nono.localhost" >> /etc/hosts
    ln -s ~/dev/kinnect.uce/config/nginx /etc/nginx/sites-available/nono.localhost
    ln -s /etc/nginx/sites-available/nono.localhost /etc/nginx/sites-enabled/
    /etc/init.d/nginx restart
    firefox public/index


