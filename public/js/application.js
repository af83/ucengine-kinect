uce.infos.get(function(err, result) {
    if (err) throw err;
    else $('#metadata').text(JSON.stringify(result));
});
