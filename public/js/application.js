uce.infos.get(function(err, result) {
    if (err) throw err;
    else $('#metadata').text(JSON.stringify(result));
});

uce.presence.create("participant", "participant", "codeweek-participant", function(err, result) {
    var session = uce.attachPresence(result);
    var meeting = session.meeting('demo');
    meeting.bind(function(event) {
        console.log("event received", event);
        // $("#UCE").append(event);
    });
    meeting.startLoop((new Date()).getTime());
});
