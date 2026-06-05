#include<stdio.h>

int main()
{
    int n, frames;

    printf("Enter number of pages: ");
    scanf("%d",&n);

    int pages[n];

    printf("Enter page reference string: ");
    for(int i=0;i<n;i++)
        scanf("%d",&pages[i]);

    printf("Enter number of frames: ");
    scanf("%d",&frames);

    int frame[frames];
    int recent[frames];

    for(int i=0;i<frames;i++)
    {
        frame[i]=-1;
        recent[i]=-1;
    }

    int faults=0;

    for(int i=0;i<n;i++)
    {
        int found=0;

        for(int j=0;j<frames;j++)
        {
            if(frame[j]==pages[i])
            {
                found=1;
                recent[j]=i;
                break;
            }
        }

        if(!found)
        {
            int pos=0;

            for(int j=1;j<frames;j++)
            {
                if(recent[j]<recent[pos])
                    pos=j;
            }

            frame[pos]=pages[i];
            recent[pos]=i;

            faults++;
        }

        printf("\n");

        for(int j=0;j<frames;j++)
            printf("%d ",frame[j]);
    }

    printf("\n\nTotal Page Faults = %d",faults);

    return 0;
}
