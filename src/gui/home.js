if (shared.loaded === null) {
    $(function() {
        shared.loaded = false;
        nprogress.start();
        console.log("in load");
        query.load((err, res) => {
            if (err) {
                nprogress.done();
            } else {
                shared.loaded = true;
                nprogress.done();
            }
        });
        console.log("out load");
    });
}

$('#search-form').submit(function(event) {
    if (!shared.loaded || !$('#search-textarea').val())
        event.preventDefault();
});

$('#search-button-lucky').click(function (event) {
    let str = $('#search-textarea').val();
    if (!shared.loaded || !str)
        return;
    query.query(str, (err, res) => {
        if (!res) return;
        query.get_doc(res[0].id, (err, res) => {
            if (!res) return;
            electron.shell.openExternal(res.url);
        });
    });
});

$('a.extern').click(function(event) {
    event.preventDefault();
    electron.shell.openExternal($(this).attr('href'));
});