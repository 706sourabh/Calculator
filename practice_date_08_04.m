function calculator_gui()
    
    fig = figure('Visible', 'off', 'Position', [300, 300, 370, 450]);
    
    
    input_field = uicontrol('Style', 'edit', 'String', '',...
                             'Position', [20, 370, 330, 50],...
                             'HorizontalAlignment', 'right');
    
    
    num_btns = cell(1, 10);
    for i = 1:9
        num_btns{i} = uicontrol('Style', 'pushbutton', 'String', num2str(i),...
                                'Position', [20+(mod(i-1, 3)*90), 290-(floor((i-1)/3)*70), 70, 50],...
                                'Callback', {@numBtn_Callback});
    end
    num_btns{10} = uicontrol('Style', 'pushbutton', 'String', '0',...
                             'Position', [110, 80, 70, 50],...
                             'Callback', {@numBtn_Callback});
    
   
    operator_btns = cell(1, 4);
    operators = {'+', '-', '*', '/'};
    for i = 1:4
        operator_btns{i} = uicontrol('Style', 'pushbutton', 'String', operators{i},...
                                     'Position', [280, 360-(i*70), 70, 50],...
                                     'Callback', {@operatorBtn_Callback});
    end
    
   
    equals_btn = uicontrol('Style', 'pushbutton', 'String', '=',...
                           'Position', [200, 80, 70, 50],...
                           'Callback', @equalsBtn_Callback);
    clear_btn = uicontrol('Style', 'pushbutton', 'String', 'C',...
                          'Position', [20, 80, 70, 50],...
                          'Callback', @clearBtn_Callback);
    
    
    fig.Visible = 'on';
    
    % Serial port configuration
    s = serialport('COM9', 9600);
    configureTerminator(s, "LF");

    % Callback functions
    function numBtn_Callback(source, ~)
        charToSend = get(source, 'String');
        updateInputField(charToSend);
        sendToPSoC(charToSend);
        
    end

    function operatorBtn_Callback(source, ~)
        charToSend = get(source, 'String');
        updateInputField(charToSend);
        sendToPSoC(charToSend);
        
    end

    function equalsBtn_Callback(source, ~)
        charToSend = get(source, 'String');
        sendToPSoC(charToSend);
        %expression = get(input_field, 'String');
        % Transmit expression to PSoC and receive result
        %result = communicateWithPSoC(expression);
       
        %set(input_field, 'String', expression);
    end

    function clearBtn_Callback(~, ~)
        set(input_field, 'String', '');
    end

%     function result = communicateWithPSoC(expression)
%         % Logic to communicate with PSoC
%         % (Same as before)
%     end

    function updateInputField(charToSend)
        current_str = get(input_field, 'String');
        new_str = strcat(current_str, charToSend);
        set(input_field, 'String', new_str);
    end

    function sendToPSoC(charToSend)
        % Print the character being sent
        fprintf('Sending character to PSoC: %s\n', charToSend);
        
        % Send character to PSoC
        write(s, charToSend, "char");

        % Update status label
        %lblStatus.Text = 'Status: Text sent to PSoC';
    end
end
