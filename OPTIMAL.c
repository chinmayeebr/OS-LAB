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

    for(int i=0;i<frames;i++)
        frame[i]=-1;

    int faults=0;

    for(int i=0;i<n;i++)
    {
        int found=0;

        for(int j=0;j<frames;j++)
        {
            if(frame[j]==pages[i])
            {
                found=1;
                break;
            }
        }

        if(!found)
        {
            int pos=-1;

            for(int j=0;j<frames;j++)
            {
                if(frame[j]==-1)
                {
                    pos=j;
                    break;
                }
            }

            if(pos==-1)
            {
                int farthest=-1;
                int replace=0;

                for(int j=0;j<frames;j++)
                {
                    int k;

                    for(k=i+1;k<n;k++)
                    {
                        if(frame[j]==pages[k])
                            break;
                    }

                    if(k==n)
                    {
                        replace=j;
                        break;
                    }

                    if(k>farthest)
                    {
                        farthest=k;
                        replace=j;
                    }
                }

                pos=replace;
            }

            frame[pos]=pages[i];
            faults++;
        }

        printf("\n");

        for(int j=0;j<frames;j++)
            printf("%d ",frame[j]);
    }

    printf("\n\nTotal Page Faults = %d",faults);

    return 0;
}
