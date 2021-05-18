% Fredrik Tåkvist
% ---------------
% set the colour of the lamps based on lamp state
function set_lights(f, d, e)
    global light1H light2H light3H light4H light5H lightDH lightEH
    light1H.FaceColor = get_color(f(1));
    light2H.FaceColor = get_color(f(2));
    light3H.FaceColor = get_color(f(3));
    light4H.FaceColor = get_color(f(4));
    light5H.FaceColor = get_color(f(5));
    lightDH.FaceColor = get_color(d*3);
    lightEH.FaceColor = get_color(e*2);

end

% turn state into colour
function c = get_color(v)
    if v == 0
        c = '#c9c9c9';
    elseif v == 1
        c = 'blue';
    elseif v == 2
        c = 'red';
    elseif v == 3
        c = 'green';
    end
end