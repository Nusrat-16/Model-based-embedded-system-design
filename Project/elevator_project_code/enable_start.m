% Fredrik Tåkvist
% --
% enable_start(e) enables/disables the start button based on e
function enable_start(e)
    global btnSH
    if e == 0
        btnSH.Enable = 'off';
    else
        btnSH.Enable = 'on';
    end
end

