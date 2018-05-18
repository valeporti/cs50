<div id="middle">
<form action="change_pass.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="old_pass" placeholder="Old Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="new_pass" placeholder="New Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Confirm Password" type="password"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Change
            </button>
        </div>
    </fieldset>
</form>
