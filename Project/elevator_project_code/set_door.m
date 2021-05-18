% Fredrik Tåkvist
% ---------------
% animate the doors opening and closing
function set_door(d)
    global liftDH
    if d == 1
        liftDH.Visible = 'On';
    else
        liftDH.Visible = 'Off';
    end
end

