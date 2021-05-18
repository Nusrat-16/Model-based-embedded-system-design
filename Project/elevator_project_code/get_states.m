% Fredrik Tåkvist
% ---------------
% get state of floor buttons
function s = get_states()
    global buttons
    s = [buttons(1) buttons(2) buttons(3) buttons(4)];
end

