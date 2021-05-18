function lift_fig(position,l1,l2,l3,l4,em,door)
% position=2;
% l1=1;l2=1;l3=1;l4=1;
% em=1;
% door=1;
% Create figure
fig=figure(1);
xlim([0 1])
ylim([1 5])
set(gca,'XTick',zeros(1,0),'YTick',[0 1 2 3 4],'GridAlpha',1,'LineWidth',2);
set(gcf,'Position',[1000 250 400 500])
box on;
grid on;
hold on


% Create title
title({'Elevator'});

% default lamps
h=plot (0.1, 1.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','k');
text(0.05, 1.2, 'Floor 1');
h=plot (0.1, 2.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','k');
text(0.05, 2.2, 'Floor 2');
h=plot (0.1, 3.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','k');
text(0.05, 3.2, 'Floor 3');
h=plot (0.1, 4.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','k');
text(0.05, 4.2, 'Floor 4');

h=plot (0.9, 3.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','k');
text(0.85, 3.2, 'Door');
h=plot ([.45 .45], [1 1.8],'k', 'lineWidth',1.5);
h=plot ([.45 .45], [2 2.8],'k', 'lineWidth',1.5);
h=plot ([.45 .45], [3 3.8],'k', 'lineWidth',1.5);
h=plot ([.45 .45], [4 4.8],'k', 'lineWidth',1.5);

h=plot (0.9, 4.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','k');
text(0.75, 4.2, 'Emergency');

% create position lamp
if l1==1
    h=plot (0.1, 1.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','c');
end
if l2==1
    h=plot (0.1, 2.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','c');
end
if l3==1
    h=plot (0.1, 3.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','c');
end
if l4==1
    h=plot (0.1, 4.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','c');
end

if door==1
    h=plot (0.9, 3.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','g');
    h=plot ([.45 .45], [position (position+.8)],'g--', 'lineWidth',1.5);
end
if em==1
    h=plot (0.9, 4.5, 'o', 'MarkerSize', 15,'MarkerFaceColor','r');    
end

% default elevators
h=plot ([0.4 0.5 0.5 0.4 0.4],[1 1 1.8 1.8 1],'k','lineWidth',2);
h=plot ([0.4 0.5 0.5 0.4 0.4],[2 2 2.8 2.8 2],'k','lineWidth',2);
h=plot ([0.4 0.5 0.5 0.4 0.4],[3 3 3.8 3.8 3],'k','lineWidth',2);
h=plot ([0.4 0.5 0.5 0.4 0.4],[4 4 4.8 4.8 4],'k','lineWidth',2);

% create rectangle
if position==1
    h=plot ([0.4 0.5 0.5 0.4 0.4],[1 1 1.8 1.8 1],'b','lineWidth',2);
elseif position==2
    h=plot ([0.4 0.5 0.5 0.4 0.4],[2 2 2.8 2.8 2],'b','lineWidth',2);
elseif position==3
    h=plot ([0.4 0.5 0.5 0.4 0.4],[3 3 3.8 3.8 3],'b','lineWidth',2);
elseif position==4
    h=plot ([0.4 0.5 0.5 0.4 0.4],[4 4 4.8 4.8 4],'b','lineWidth',2);
    grid on;
end
hold off
hold off
